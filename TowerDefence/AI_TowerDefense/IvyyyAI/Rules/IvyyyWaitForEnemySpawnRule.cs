using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using tower_defence.AI_TowerDefense.IvyyyAI;

namespace AI_Strategy
{
    public class IvyyyWaitForEnemySpawnRule : IvyyyRule
    {
        public IvyyyWaitForEnemySpawnRule (TowerDefenseAgentState state) : base (state)
        {
            m_axis.Add(new IvyyyRuleAxis("StartPhase", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));
            m_axis.Add(new IvyyyRuleAxis("NoEnemyActive", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));
            m_axis.Add(new IvyyyRuleAxis("NoTowerActive", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));
            m_weight = 10f;
        }

        public override void Action(object target)
        {
        }
    }
}
