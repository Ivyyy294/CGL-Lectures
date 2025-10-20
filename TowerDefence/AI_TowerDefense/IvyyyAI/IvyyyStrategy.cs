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
        private enum Goal
        {
            BuildTower,
            CalculateRegimentSettings,
            BuildSoldiers,
            DeploySoldiers,
            NULL
        }

        private Goal m_goal;

        //Rules
        IvyyyUpdateRegimentRule m_updateRegimentRule;
        IvyyyBuildRegimentRule m_buildRegimentRule;
        IvyyyBuildTowerRule m_buildTowerRule;
        //

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

            m_updateRegimentRule = new IvyyyUpdateRegimentRule (m_activeRegimentSettings, m_worldState);
            m_buildRegimentRule = new IvyyyBuildRegimentRule (m_activeRegimentSettings, m_worldState);
            m_buildTowerRule = new IvyyyBuildTowerRule (m_worldState);
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
            m_worldState.Update(m_perception);
            UpdateGoal(ref m_goal, ref m_worldState);
            Action action = SelectAction(m_goal);
            
            if (action != null)
                action();
        }

        private void UpdateGoal (ref Goal goal, ref TowerDefenseAgentState worldState)
        {
            if (goal == Goal.NULL)
                goal = Goal.BuildTower;
            else if (goal == Goal.BuildTower)
            {
                if (worldState.ActionTyp == TowerDefensePerception.ActionTyp.TurnEnd)
                    goal = Goal.CalculateRegimentSettings;
            }
            else if (goal == Goal.CalculateRegimentSettings)
                goal = Goal.BuildSoldiers;
            else if (goal == Goal.BuildSoldiers)
            {
                if (m_activeRegimentSettings.IsRegimentComplete())
                    goal = Goal.DeploySoldiers;
            }
            else if (goal == Goal.DeploySoldiers)
            {
                if (m_worldState.ActionTyp == TowerDefensePerception.ActionTyp.DeployTowers)
                    goal = Goal.BuildTower;
            }
        }

        private Action SelectAction (Goal goal)
        {
            if (goal == Goal.NULL)
                return null;
            else if (goal == Goal.CalculateRegimentSettings)
                return m_updateRegimentRule.CalculateRegimentSettings;
            else if (goal == Goal.BuildSoldiers)
            {
                if (m_worldState.ActionTyp == TowerDefensePerception.ActionTyp.DeploySoldiers)
                    return m_buildRegimentRule.BuildRegiment;
                else
                    return null;
            }
            else if (goal == Goal.DeploySoldiers)
                return DeployRegiment;
            else if (goal == Goal.BuildTower)
            {
                if (m_worldState.ActionTyp == TowerDefensePerception.ActionTyp.DeployTowers)
                    return m_buildTowerRule.DeployTowers;
            }

            return null;
        }

        private void DeployRegiment()
        {
            DebugLogger.Log("#Player" + m_perception.Player.Name + " Deploy Regiment!");
            m_activeRegimentSettings.Deploy();
        }
    }
}
