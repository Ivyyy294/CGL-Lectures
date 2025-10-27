using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public abstract class IvyyyRule
    {
        protected List<string> m_inputParameter = new();
        protected float m_weight = 1.0f;
        protected string m_target = null;

        public float Weight => m_weight;
        public string Target => m_target;

        protected TowerDefenseAgentState m_worldState;

        public IvyyyRule (TowerDefenseAgentState worldState)
        {
            m_worldState = worldState;
        }

        public abstract void Action();

        public float Match(object target)
        {
            float match = 1.0f;

            if (m_inputParameter.Count == 0)
                return 0f;

            foreach (string inputParameter in m_inputParameter)
                match *= m_worldState.GetActionInputParameter(inputParameter, target);

            return match;
        }
    }
}
