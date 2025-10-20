using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class IvyyyDeployRegimentRule : IvyyyRule
    {
        private ActiveRegimentSettings m_activeRegimentSettings;

        public IvyyyDeployRegimentRule(ActiveRegimentSettings activeRegimentSettings, TowerDefenseAgentState state) : base(state)
        {
            m_activeRegimentSettings = activeRegimentSettings;
        }

        public override void Action()
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Deploy Regiment!");
            m_activeRegimentSettings.Deploy();
        }

        public override bool MatchRule(IvyyyStrategy.Goal goal)
        {
            return goal == IvyyyStrategy.Goal.DeploySoldiers;
        }
    }
}
