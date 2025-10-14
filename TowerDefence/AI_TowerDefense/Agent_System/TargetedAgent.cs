using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public class TargetedAgent<TPerception, TState> : ObservingAgent<TPerception, TState> where TState : AgentState<TPerception>, new()
    {
        protected List <AgentGoal<TState>> m_goals;

        public void SetGoals (List<AgentGoal<TState>> goals)
        {
            m_goals = goals;
        }

        public override Action SelectAction(TPerception perception)
        {
            m_state.Update (perception);
            AgentRule<TState> rule = MatchRule(ref m_state);

            if (rule == null)
                return null;

            Action action = rule.GetAction();
            return action;
        }

        protected override AgentRule<TState> MatchRule(ref TState state)
        {
            for (int i = 0; i < m_goals.Count; ++i)
            {
                var goal = m_goals[i];

                for (int j = 0; j < m_rules.Count; j++)
                {
                    AgentRule<TState> rule = m_rules[i];
                    if (rule != null && rule.Match(state, goal))
                        return rule;
                }
            }

            return null;
        }
    }
}
