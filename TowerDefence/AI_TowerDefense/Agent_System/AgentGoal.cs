using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public abstract class AgentGoal <TState>
    {
        protected int m_weight = 0;
        public int Weight => m_weight;

        public virtual void UpdateWeight (TState state) {}
    }
}
