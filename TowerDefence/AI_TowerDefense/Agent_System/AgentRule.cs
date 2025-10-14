using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public abstract class AgentRule <TState>
    {
        public abstract bool Match (TState state);
        public abstract bool Match (TState state, AgentGoal<TState> goal);
        public abstract Action GetAction();
    }
}
