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
            m_axis.Add(new IvyyyRuleAxis("GetGold", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Logistic, 100f, -1f, 1f, 0.5f)));
        }

        public override void Action(object target)
        {
        }
    }
}
