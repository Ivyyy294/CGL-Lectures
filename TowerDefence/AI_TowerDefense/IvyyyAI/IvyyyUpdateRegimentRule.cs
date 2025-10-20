using System;

namespace AI_Strategy
{
    public class IvyyyUpdateRegimentRule
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        private TowerDefenseAgentState m_worldState;

        public IvyyyUpdateRegimentRule (ActiveRegimentSettings activeRegimentSettings, TowerDefenseAgentState state)
        {
            m_activeRegimentSettings = activeRegimentSettings;
            m_worldState = state;
        }

        public void CalculateRegimentSettings()
        {
            EvaluateRegimentSize();
            SetRegimentStartIndex();
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
