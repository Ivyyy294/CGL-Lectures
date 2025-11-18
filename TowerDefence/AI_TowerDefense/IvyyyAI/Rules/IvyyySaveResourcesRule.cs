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
            m_axis.Add(new IvyyyRuleAxis("GetGold", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 4f, 1f, 0f)));
        }

        public override void Action(object target)
        {
        }
    }
}
