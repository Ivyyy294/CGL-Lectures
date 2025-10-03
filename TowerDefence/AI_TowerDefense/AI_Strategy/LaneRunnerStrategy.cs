using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace AI_Strategy
{
    public class LaneRunnerStrategy : AbstractStrategy
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        public LaneRunnerStrategy(Player player) : base(player)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.AddInstance(player.Name);
            m_activeRegimentSettings.Width = 3;
            m_activeRegimentSettings.Depth = 4;
            m_activeRegimentSettings.SoldierLane = player.EnemyLane;
        }
        public override void DeploySoldiers()
        {
            if (player.Gold < m_activeRegimentSettings.Width * 2)
                return;

            for (int i = 0; i < m_activeRegimentSettings.Width; ++i)
                player.TryBuySoldier<DummySoldier>(m_activeRegimentSettings.StartIndex + i);
        }

        public override void DeployTowers()
        {
        }

        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList;
        }

        private bool AllTowersPlaced()
        {
            return player.HomeLane.TowerCount() >= GetTargetTowerCount();
        }

        private int GetTargetTowerCount()
        {
            return 3;
        }
    }
}
