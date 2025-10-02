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
        public static int regimentStartIndex = 0;
        public static int regimentWidth = 3;
        public static int regimentDepth = 3;

        private int m_soldierLaneIndex = 0;
        public DummyStrategy(Player player) : base(player)
        {

        }


        public override void DeploySoldiers()
        {
            if (!AllTowersPlaced())
                return;

            if (player.Gold < regimentWidth * 2)
                return;

            for (int i = 0; i < regimentWidth; ++i)
                player.TryBuySoldier<DummySoldier>(regimentStartIndex + i);
        }

        public override void DeployTowers()
        {
            if (AllTowersPlaced())
                return;

            for (int i = 1; i <= 13 && player.Gold >= 8; ++i)
            {
                int laneOffset = i / PlayerLane.WIDTH;
                int lane = 17 - (laneOffset * 2);
                int row = i - (PlayerLane.WIDTH * laneOffset);

                player.TryBuyTower<Tower>(row, lane);

                if (m_soldierLaneIndex < PlayerLane.WIDTH - 1)
                    m_soldierLaneIndex+=2;
            }
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
            int towerPerBlock = 7;
            int goldPerBlock = towerPerBlock * 8;
            int blockCount = Math.Max (1, player.Gold / goldPerBlock);
            return blockCount * towerPerBlock;
        }
    }
}
