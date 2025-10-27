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
        private List<IvyyyRule> m_rules = new();
        private List<Tuple<float, Action>> m_ratedActions = new();

        private TowerDefenseAgentState m_worldState = new();
        private TowerDefensePerception m_perception = new();
        
        public IvyyyStrategy(Player player) : base(player)
        {
            m_perception.Player = player;

            m_rules.Add (new IvyyyUpdateRegimentRule (m_worldState));
            m_rules.Add(new IvyyyBuildRegimentRule (m_worldState));
            m_rules.Add(new IvyyyDeployRegimentRule (m_worldState));
            m_rules.Add(new IvyyyBuildTowerRule (m_worldState));
            m_rules.Add(new IvyyyWaitForEnemySpawnRule (m_worldState));
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
            Action lastAction = null;

            while (true)
            {
                m_worldState.Update(m_perception);

                RateActions();

                Action action = SelectAction();
            
                if (lastAction == action
                    || action == null)
                    return;
                else
                {
                    action();
                    lastAction = action;
                }
            }
        }

        private Action SelectAction ()
        {
            if (m_ratedActions.Count > 0
                && m_ratedActions[0].Item1 > 0f)
            {
                return m_ratedActions[0].Item2;
            }

            return null;
        }

        private void RateActions ()
        {
            m_ratedActions.Clear();

            foreach (var rule in m_rules)
            {
                if (rule.Target == null)
                    m_ratedActions.Add (new Tuple<float, Action> (rule.Match (null) * rule.Weight, rule.Action));
                else
                {
                    List<object> targetList = m_worldState.GetTargetList (rule.Target);

                    foreach (var target in targetList)
                        m_ratedActions.Add(new Tuple<float, Action>(rule.Match(target) * rule.Weight, rule.Action));
                }
            }

            m_ratedActions = m_ratedActions.OrderByDescending (x=>x.Item1).ToList<Tuple<float, Action>>();
        }
    }
}
