using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using tower_defence.AI_TowerDefense.IvyyyAI;

namespace AI_Strategy
{
    public abstract class IvyyyRule
    {
        protected List<IvyyyRuleAxis> m_axis = new();
        protected float m_weight = 1.0f;
        protected string m_target = null;

        public float Weight => m_weight;
        public string Target => m_target;

        protected TowerDefenseAgentState m_worldState;

        public IvyyyRule (TowerDefenseAgentState worldState)
        {
            m_worldState = worldState;
        }

        public abstract void Action(object target);

        public float Match(object target)
        {
            float match = 1.0f;

            if (m_axis.Count == 0)
                return 0f;

            foreach (IvyyyRuleAxis axis in m_axis)
            {
                float x = m_worldState.GetActionInputParameter(axis.Parameter, target);
                match *= axis.ResponseCurve.Evaluate (x);
            }

            return match;
        }
    }
}
