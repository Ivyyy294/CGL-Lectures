using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IvyyyAI
{
    public class IvyyySaveResourcesRule : IvyyyRule
    {
        public IvyyySaveResourcesRule(IvyyyWorldState worldState) : base(worldState)
        {
            m_weight = 3f;
            m_target = "AttackLanes";
            m_axis.Add(new IvyyyRuleAxis("CanBuyRegiment", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 25f, 1f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("LaneRowCounter", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1000f, 10f, 0f, 0.5f)));
        }

        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Save Gold!");
        }
    }
}
