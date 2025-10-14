using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public class ObservingAgent<TPerception, TState> : Agent<TPerception, TState> where TState : AgentState<TPerception>, new()
    {
        protected TState m_state = new TState();

        public TState State => m_state;

        public override Action SelectAction(TPerception perception)
        {
            m_state.Update(perception);
            AgentRule<TState> rule = MatchRule(ref m_state);

            if (rule == null)
                return null;

            Action action = rule.GetAction();
            return action;
        }
    }
}
