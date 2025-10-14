using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public abstract class Agent<TPerception, TState> where TState : AgentState<TPerception>
    {
        protected List<AgentRule<TState>> m_rules = new();

        public void SetRules (List<AgentRule<TState>> rules)
        {
            m_rules = rules;
        }

        public void AddRule(AgentRule<TState> rule)
        {
            m_rules.Add(rule);
        }

        public abstract Action SelectAction (TPerception perception);

        protected virtual AgentRule<TState> MatchRule(ref TState state)
        {
            for (int i = 0; i < m_rules.Count; i++)
            {
                AgentRule <TState> rule = m_rules[i];
                if (rule != null && rule.Match(state))
                    return rule;
            }

            return null;
        }
    }
}
