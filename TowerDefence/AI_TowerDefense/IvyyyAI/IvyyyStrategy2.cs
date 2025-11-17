using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IvyyyAI
{
    public class IvyyyStrategy2 : AI_Strategy.AbstractStrategy
    {
     
        bool bla = true;
        int counter = 0;

        public IvyyyStrategy2(Player player) : base(player)
        {
        }
        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }

        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)
        {
            return unsortedList.OrderByDescending(s => s.PosY).ToList();
        }


        public override void DeploySoldiers()
        {
            //player.TryBuySoldier<Soldier>(0);
            //player.TryBuySoldier<Soldier>(1);
            //player.TryBuySoldier<Soldier>(2);
            //player.TryBuySoldier<Soldier>(3);
            //player.TryBuySoldier<Soldier>(4);
            //player.TryBuySoldier<Soldier>(5);
            //player.TryBuySoldier<Soldier>(6);

            if (counter > 0)
            {
                player.TryBuySoldier<Soldier>(0);
                player.TryBuySoldier<Soldier>(1);
                player.TryBuySoldier<Soldier>(2);
            }

            counter++;
            //if (bla)
            //    player.TryBuySoldier<IvyyySoldier>(0);

            //bla = !bla;
        }

        public override void DeployTowers()
        {
            for (int c = 3; c < PlayerLane.HEIGHT; ++c)
            {
                player.TryBuyTower<Tower>(2, c);
                player.TryBuyTower<Tower>(3, c);
                player.TryBuyTower<Tower>(4, c);
            }
        }
    }
}
