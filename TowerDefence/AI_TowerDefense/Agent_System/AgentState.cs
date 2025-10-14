using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public abstract class AgentState <TPerception>
    {
        public abstract void Update (TPerception perception);
    }
}
