using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public abstract class StrategyState
    {
        protected StrategyStateMachine m_stateMachine;
        protected Player m_player;

        public StrategyState (StrategyStateMachine stateMachine)
        {
            m_stateMachine = stateMachine;
            m_player = m_stateMachine.Player;
        }

        public abstract void Continue();
        public abstract void Enter();
        public abstract void Exit();
        public abstract void DeployTowers();
        public abstract void DeploySoldiers();

    }
}
