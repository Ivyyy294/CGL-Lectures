using Agent_Test;
using GameFramework;

namespace AI_Strategy
{
    public class IvyyyBuildRegimentRule : IvyyyRule
    {
        public IvyyyBuildRegimentRule(TowerDefenseAgentState state) : base(state)
        {
            m_inputParameter.Add ("CanBuySoldiers");
            m_inputParameter.Add ("DeploySoldiers");
        }

        public override void Action(object target)
        {
            ActiveRegimentSettings activeRegimentSettings = m_worldState.ActiveRegimentSettings;
            
            if (m_worldState.Gold < activeRegimentSettings.Width * 2)
                return;

            for (int i = 0; i < activeRegimentSettings.Width; ++i)
            {
                int xPos = activeRegimentSettings.StartIndex + i;
                Player.SoldierPlacementResult result = m_worldState.Player.TryBuySoldier<IvyyySoldier>(xPos);

                if (result == Player.SoldierPlacementResult.Success)
                {
                    Cell cell = m_worldState.Player.EnemyLane.GetCellAt(xPos, 0);
                    IvyyySoldier soldier = (IvyyySoldier)cell.Unit;
                    soldier.SetRegimentSettings(activeRegimentSettings);
                    activeRegimentSettings.m_soldiers.Add(soldier);
                }
            }

        }
    }
}
