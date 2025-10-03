using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace AI_Strategy
{
    public class DummyStrategy : AbstractStrategy
    {
        private ActiveRegimentSettings m_activeRegimentSettings;
        public DummyStrategy(Player player) : base(player)
        {
            m_activeRegimentSettings = ActiveRegimentSettings.AddInstance (player.Name);
            m_activeRegimentSettings.Width = 3;
            m_activeRegimentSettings.Depth = 4;
            m_activeRegimentSettings.SoldierLane = player.EnemyLane;
        }
        public override void DeploySoldiers()
        {
            if (!AllTowersPlaced())
                return;

            if (player.Gold < m_activeRegimentSettings.Width * 2)
                return;

            for (int i = 0; i < m_activeRegimentSettings.Width; ++i)
                player.TryBuySoldier<DummySoldier>(m_activeRegimentSettings.StartIndex + i);
        }

        public override void DeployTowers()
        {
            if (AllTowersPlaced())
                return;

            player.TryBuyTower<Tower>(3, 10);
            player.TryBuyTower<Tower>(3, 12);
            player.TryBuyTower<Tower>(3, 14);

            

            //for (int i = 1; i <= 13 && player.Gold >= 8; ++i)
            //{
            //    int laneOffset = i / PlayerLane.WIDTH;
            //    int lane = 17 - (laneOffset * 2);
            //    int row = i - (PlayerLane.WIDTH * laneOffset);

            //    player.TryBuyTower<Tower>(row, lane);

            //    if (m_soldierLaneIndex < PlayerLane.WIDTH - 1)
            //        m_soldierLaneIndex+=2;
            //}
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
            int towerPerBlock = 7;
            int goldPerBlock = towerPerBlock * 8;
            int blockCount = Math.Max (1, player.Gold / goldPerBlock);
            return blockCount * towerPerBlock;
        }
    }
}
