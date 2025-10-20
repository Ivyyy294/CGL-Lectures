using Agent_Test;
using GameFramework;

namespace AI_Strategy
{
    public class IvyyyBuildRegimentRule : IvyyyRule
    {
        private ActiveRegimentSettings m_activeRegimentSettings;

        public IvyyyBuildRegimentRule(ActiveRegimentSettings activeRegimentSettings, TowerDefenseAgentState state) : base(state)
        {
            m_activeRegimentSettings = activeRegimentSettings;
        }

        public override void Action()
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

        public override bool MatchRule(IvyyyStrategy.Goal goal)
        {
            return goal == IvyyyStrategy.Goal.BuildSoldiers
                && m_worldState.ActionTyp == TowerDefensePerception.ActionTyp.DeploySoldiers;
        }
    }
}
