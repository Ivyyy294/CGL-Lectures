using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public abstract class StrategyStateMachine : AbstractStrategy
    {
        protected List<StrategyState> m_states = new();
        public Player Player => player;
        public StrategyStateMachine (Player player): base (player)
        {}
        public void Push (StrategyState state)
        {
            if (state == null)
                return;

            m_states.Add (state);
            state.Enter();
        }
        public void Pop()
        {
            if (m_states.Count == 0)
                return;

            m_states.Last().Exit();
            m_states.RemoveAt(m_states.Count - 1);

            if (m_states.Count == 0)
                return;

            m_states.Last().Continue();
        }
        public override void DeploySoldiers()
        {
            if (m_states.Count == 0)
                return;

            m_states.Last().DeploySoldiers();
        }

        public override void DeployTowers()
        {
            if (m_states.Count == 0)
                return;

            m_states.Last().DeployTowers();
        }
    }
}
