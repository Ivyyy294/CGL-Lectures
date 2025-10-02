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
        private int m_soldierLaneIndex = 0;
        public LaneRunnerStrategy(Player player) : base(player)
        {

        }
        public override void DeploySoldiers()
        {
            if (player.Gold < DummyStrategy.regimentWidth * 2)
                return;

            for (int i = 0; i < DummyStrategy.regimentWidth; ++i)
                player.TryBuySoldier<DummySoldier>(DummyStrategy.regimentStartIndex + i);
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
