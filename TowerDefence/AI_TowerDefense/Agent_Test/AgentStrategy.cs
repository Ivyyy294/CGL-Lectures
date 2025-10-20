using Agent_System;
using Agent_Test;
using AI_Strategy;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace tower_defence.AI_TowerDefense.AI_Strategy
{
    public class AgentStrategy : AbstractStrategy
    {
        TowerDefensePerception m_perception = new();
        ObservingAgent <TowerDefensePerception, TowerDefenseAgentState> m_agent = new();

        public AgentStrategy(Player player) : base(player)
        {
            m_agent.AddRule(new BuildSoldierRule(player));
            m_perception.Player = player;
        }

        public override void DeploySoldiers()
        {
            m_perception.CurrentActionTyp = TowerDefensePerception.ActionTyp.DeployTowers;
            Action action = m_agent.SelectAction (m_perception);
            
            if (action == null)
                return;

            action();
        }

        public override void DeployTowers()
        {
            m_perception.CurrentActionTyp = TowerDefensePerception.ActionTyp.DeployTowers;

            Action action = m_agent.SelectAction(m_perception);

            if (action == null)
                return;

            action();
        }

        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList;
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList;
        }
    }
}
