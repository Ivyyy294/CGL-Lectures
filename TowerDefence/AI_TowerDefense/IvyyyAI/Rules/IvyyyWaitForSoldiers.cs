using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IvyyyAI
{
    public class IvyyyWaitForSoldiers : IvyyyRule
    {
        public IvyyyWaitForSoldiers(IvyyyWorldState worldState) : base(worldState)
        {
            m_weight = 10f;

            m_axis.Add(new IvyyyRuleAxis("TurnCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 20f, 1f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("EnemyCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 20f, 0f, 1f)));
        }

        public override void Action(object target)
        {

        }
    }
}
