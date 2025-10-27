using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class IvyyyWaitForEnemySpawnRule : IvyyyRule
    {
        public IvyyyWaitForEnemySpawnRule (TowerDefenseAgentState state) : base (state)
        {
            m_inputParameter.Add ("StartPhase");
            m_inputParameter.Add ("NoEnemyActive");
            m_inputParameter.Add ("NoTowerActive");
            m_weight = 10f;
        }

        public override void Action(object target)
        {
        }
    }
}
