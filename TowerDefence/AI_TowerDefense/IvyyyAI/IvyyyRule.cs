using System.Collections.Generic;

namespace IvyyyAI
{
    public abstract class IvyyyRule
    {
        protected List<IvyyyRuleAxis> m_axis = new();
        protected float m_weight = 1.0f;
        protected string m_target = null;

        public float Weight => m_weight;
        public string Target => m_target;

        protected IvyyyWorldState m_worldState;

        public IvyyyRule (IvyyyWorldState worldState)
        {
            m_worldState = worldState;
        }

        public abstract void Action(object target);

        public float Match(object target)
        {
            float modFactor = 1f - (1f / m_axis.Count);
            float match = 1.0f;

            if (m_axis.Count == 0)
                return 0f;

            foreach (IvyyyRuleAxis axis in m_axis)
            {
                float x = m_worldState.GetActionInputParameter(axis.Parameter, target);
                float score = axis.ResponseCurve.Evaluate(x);
                float makeUpValue = (1f - score) * modFactor;
                score += makeUpValue * score;
                match *= score;
            }

            return match;
        }
    }
}
