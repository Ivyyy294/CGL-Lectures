using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class IvyyyDeployRegimentRule : IvyyyRule
    {
        public IvyyyDeployRegimentRule(TowerDefenseAgentState state) : base(state)
        {
            m_inputParameter.Add ("RegimentComplete");
            m_inputParameter.Add ("DeploySoldiers");
            m_weight = 10f;
        }

        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Deploy Regiment!");
            m_worldState.ActiveRegimentSettings.Deploy();
            m_worldState.ActiveRegimentSettings = null;
        }
    }
}
