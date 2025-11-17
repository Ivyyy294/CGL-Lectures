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
            m_axis.Add(new IvyyyRuleAxis("GetGold", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.4f, 4f, 0f, 1f)));
        }

        public override void Action(object target)
        {
        }
    }
}
