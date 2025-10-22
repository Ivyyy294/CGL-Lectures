using Agent_Test;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing.Reader;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace AI_Strategy
{
    public class IvyyyStrategy : AbstractStrategy
    {
        public enum Goal
        {
            BuildTower,
            CalculateRegimentSettings,
            BuildSoldiers,
            DeploySoldiers,
            NULL
        }

        private int m_turn = 0;
        private Goal m_goal = Goal.NULL;
        private List<IvyyyRule> m_rules = new();

        private TowerDefenseAgentState m_worldState = new();
        private TowerDefensePerception m_perception = new();

        private ActiveRegimentSettings m_activeRegimentSettings;
        public IvyyyStrategy(Player player) : base(player)
        {
            m_perception.Player = player;
            
            m_activeRegimentSettings = ActiveRegimentSettings.AddInstance (player.Name);
            m_activeRegimentSettings.Width = 2;
            m_activeRegimentSettings.Depth = 3;
            m_activeRegimentSettings.StartIndex = 0;
            m_activeRegimentSettings.SoldierLane = player.EnemyLane;

            m_rules.Add (new IvyyyUpdateRegimentRule (m_activeRegimentSettings, m_worldState));
            m_rules.Add(new IvyyyBuildRegimentRule (m_activeRegimentSettings, m_worldState));
            m_rules.Add(new IvyyyDeployRegimentRule (m_activeRegimentSettings, m_worldState));
            m_rules.Add(new IvyyyBuildTowerRule (m_worldState));
        }
        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public void StartTurn()
        {
            m_perception.CurrentActionTyp = TowerDefensePerception.ActionTyp.TurnStart;
            AgentLoop();
        }

        public void EndTurn()
        {
            m_perception.CurrentActionTyp = TowerDefensePerception.ActionTyp.TurnEnd;
            AgentLoop();
            m_turn++;
        }

        public override void DeploySoldiers()
        {
            m_perception.CurrentActionTyp = TowerDefensePerception.ActionTyp.DeploySoldiers;

            AgentLoop();

            EndTurn();
        }

        public override void DeployTowers()
        {
            StartTurn();

            m_perception.CurrentActionTyp = TowerDefensePerception.ActionTyp.DeployTowers;

            AgentLoop();
        }

        //Private Methods
        private void AgentLoop()
        {
            while (true)
            {
                Goal prevGoal = m_goal;
                m_worldState.Update(m_perception);
                UpdateGoal(ref m_goal, ref m_worldState);
                Action action = SelectAction(m_goal);
            
                if (action != null)
                    action();
                
                if (m_goal == prevGoal
                    || action == null)
                    return;
            }
        }

        private void UpdateGoal (ref Goal goal, ref TowerDefenseAgentState worldState)
        {
            if (goal == Goal.NULL)
            {
                if (worldState.EnemyCount > 0 || m_turn > 2)
                  goal = Goal.BuildTower;
            }
            else if (goal == Goal.BuildTower)
            {
                int goldRequired = worldState.GetTowerCost(4 - worldState.BestDefensePerimeter.TowerCount);

                if (worldState.Gold < goldRequired
                    || worldState.ActionTyp == TowerDefensePerception.ActionTyp.DeploySoldiers)
                    goal = Goal.CalculateRegimentSettings;
            }
            else if (goal == Goal.CalculateRegimentSettings)
            {
                goal = Goal.BuildSoldiers;
            }
            else if (goal == Goal.BuildSoldiers)
            {
                if (m_activeRegimentSettings.IsRegimentComplete())
                    goal = Goal.DeploySoldiers;
            }
            else if (goal == Goal.DeploySoldiers)
            {
                goal = Goal.BuildTower;
            }
        }

        private Action SelectAction (Goal goal)
        {
            for (int i = 0; i < m_rules.Count; ++i)
            {
                if (m_rules[i].MatchRule (goal))
                    return m_rules[i].Action;
            }

            return null;
        }
    }
}
