using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using tower_defence.AI_TowerDefense.IvyyyAI;

namespace AI_Strategy
{
    public class IvyyyDeployRegimentRule : IvyyyRule
    {
        public IvyyyDeployRegimentRule(TowerDefenseAgentState state) : base(state)
        {
            m_axis.Add(new IvyyyRuleAxis("RegimentComplete", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
            m_axis.Add(new IvyyyRuleAxis("DeploySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
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
