using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public abstract class StrategyState
    {
        public abstract void Enter();
        public abstract void Exit();
        public abstract void DeployTowers();
        public abstract void DeploySoldiers();

    }
}
