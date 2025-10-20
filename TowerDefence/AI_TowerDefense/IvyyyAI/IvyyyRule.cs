using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public abstract class IvyyyRule
    {
        protected TowerDefenseAgentState m_worldState;

        public IvyyyRule (TowerDefenseAgentState worldState)
        {
            m_worldState = worldState;
        }

        public abstract bool MatchRule (IvyyyStrategy.Goal goal);
        public abstract void Action();
    }
}
