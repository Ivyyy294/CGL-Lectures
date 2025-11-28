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

            //Reduce score to zero when required gold is gathered
            m_axis.Add(new IvyyyRuleAxis("CanBuyRegiment", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 25f, 1f, 0f)));

            //Reduces score to zero if row counter is greater as 0
            m_axis.Add(new IvyyyRuleAxis("LaneRowCounter", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1000f, 10f, 0f, 0.5f)));

            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.1f, 2f, 1f, 1f)));

            m_axis.Add(new IvyyyRuleAxis("LaneSuccessFactor", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -6f, 4f, 1f, 0.6f)));
        }

        //Do nothing
        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Save Gold!");
        }
    }
}
