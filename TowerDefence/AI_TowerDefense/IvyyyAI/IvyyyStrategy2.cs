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
            if (counter > 5)
            {
                player.TryBuySoldier<IvyyySoldier>(0);
                player.TryBuySoldier<IvyyySoldier>(1);
                player.TryBuySoldier<IvyyySoldier>(2);
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
