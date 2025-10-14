using System;

namespace Agent_System
{
    public class ReflexAgent<TPerception, TState> : Agent<TPerception, TState> where TState : AgentState<TPerception>, new()
    {
        public override Action SelectAction(TPerception perception)
        {
            TState state = new TState();
            state.Update (perception);
            AgentRule<TState> rule = MatchRule (ref state);

            if (rule == null)
                return null;

            Action action = rule.GetAction();
            return action;
        }
    }
}
