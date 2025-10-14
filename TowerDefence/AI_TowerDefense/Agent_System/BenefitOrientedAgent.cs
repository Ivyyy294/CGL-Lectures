using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_System
{
    public class BenefitOrientedAgent<TPerception, TState> : TargetedAgent<TPerception, TState> where TState : AgentState<TPerception>, new()
    {
        public override Action SelectAction(TPerception perception)
        {
            m_state.Update(perception);
            UpdateGoalWeights (m_state);

            AgentRule<TState> rule = MatchRule(ref m_state);

            if (rule == null)
                return null;

            Action action = rule.GetAction();
            return action;
        }

        protected void UpdateGoalWeights (TState state)
        {
            for (int i = 0; i < m_goals.Count; i++)
            {
                if (m_goals[i] != null)
                    m_goals[i].UpdateWeight(state);
            }

            m_goals = m_goals.OrderBy(i => i.Weight).ToList();
        }
    }
}
