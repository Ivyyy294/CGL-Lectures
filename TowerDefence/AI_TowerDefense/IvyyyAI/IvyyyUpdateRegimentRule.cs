using System;

namespace AI_Strategy
{
    public class IvyyyUpdateRegimentRule : IvyyyRule
    {
        private ActiveRegimentSettings m_activeRegimentSettings;

        public IvyyyUpdateRegimentRule (ActiveRegimentSettings activeRegimentSettings, TowerDefenseAgentState state) : base (state)
        {
            m_activeRegimentSettings = activeRegimentSettings;
        }

        public override void Action()
        {
            EvaluateRegimentSize();
            SetRegimentStartIndex();
        }

        public override bool MatchRule(IvyyyStrategy.Goal goal)
        {
            return goal == IvyyyStrategy.Goal.CalculateRegimentSettings;
        }

        private void EvaluateRegimentSize()
        {
            if (m_worldState.Gold >= 42)
                m_activeRegimentSettings.Width = 7;
            else if (m_worldState.Gold >= 36)
                m_activeRegimentSettings.Width = 6;
            else if (m_worldState.Gold >= 30)
                m_activeRegimentSettings.Width = 5;
            else if (m_worldState.Gold >= 24)
                m_activeRegimentSettings.Width = 4;
            else
                m_activeRegimentSettings.Width = 3;
        }

        private void SetRegimentStartIndex()
        {
            Random r = new Random();
            m_activeRegimentSettings.StartIndex = r.Next(0, 7 - m_activeRegimentSettings.Width);
        }
    }
}
