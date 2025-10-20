using Agent_Test;
using GameFramework;

namespace AI_Strategy
{
    public class IvyyyBuildRegimentRule
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        private TowerDefenseAgentState m_worldState;

        public IvyyyBuildRegimentRule(ActiveRegimentSettings activeRegimentSettings, TowerDefenseAgentState state)
        {
            m_activeRegimentSettings = activeRegimentSettings;
            m_worldState = state;
        }

        public void BuildRegiment()
        {
            if (m_worldState.Gold < m_activeRegimentSettings.Width * 2)
                return;

            for (int i = 0; i < m_activeRegimentSettings.Width; ++i)
            {
                int xPos = m_activeRegimentSettings.StartIndex + i;
                Player.SoldierPlacementResult result = m_worldState.Player.TryBuySoldier<IvyyySoldier>(xPos);

                if (result == Player.SoldierPlacementResult.Success)
                {
                    Cell cell = m_worldState.Player.EnemyLane.GetCellAt(xPos, 0);
                    IvyyySoldier soldier = (IvyyySoldier)cell.Unit;
                    soldier.SetRegimentSettings(m_activeRegimentSettings);
                    m_activeRegimentSettings.m_soldiers.Add(soldier);
                }
            }
        }
    }
}
