using Agent_System;
using AI_Strategy;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_Test
{
    internal class BuildSoldierRule : AgentRule<TowerDefenseAgentState>
    {
        private Player m_player;

        public BuildSoldierRule (Player player)
        {
            m_player = player;
        }

        public override Action GetAction()
        {
            return BuySoldier;
        }

        public override bool Match(TowerDefenseAgentState state)
        {
            return state.ActionTyp == TowerDefensePerception.ActionTyp.DeployTowers && state.Gold >= 2;
        }

        public override bool Match(TowerDefenseAgentState state, AgentGoal<TowerDefenseAgentState> goal)
        {
            return Match (state);
        }

        private void BuySoldier ()
        {
            Player.SoldierPlacementResult result = m_player.TryBuySoldier<Soldier>(0);
        }
    }
}
