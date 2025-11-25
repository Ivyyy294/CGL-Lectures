using System;
using GameFramework;
using System.Collections.Generic;

namespace AI_Strategy
{
    /*
     * very simple example strategy based on random placement of units.
     */
    public class GongiStratIsolated : AbstractStrategy
    {
        private static Random random = new Random();

        private bool m_sendingAttack;
        private int m_attackRound = 0;
        private int m_amountOfAttackRounds = 3;

        private int m_defenseLaneAmount;
        private int m_defenseLaneStart;
        private int m_defenseLaneDirection; // -1 = up, 1 = down

        public GongiStratIsolated(Player player) : base(player)
        {
            m_amountOfAttackRounds = 8;
            m_defenseLaneAmount = 3;
            m_defenseLaneDirection = 1;
            m_defenseLaneStart = 8;
        }

        public static int[] ShortFormation = new int[]
        {
            1,3,5
        };

        public static int[] LongFormation = new int[]
        {
            0,2,4,6
        };

        /*
         * example strategy for deploying Towers based on random placement and budget.
         * Your one should be better!
         */
        public override void DeployTowers()
        {

            for (int i = 0; i < m_defenseLaneAmount; i++)
            {
                if (i % 2 == 0)
                {
                    for (int j = 0; j < LongFormation.Length; j++)
                    {
                        int x = LongFormation[j];
                        int y = m_defenseLaneStart + (i * m_defenseLaneDirection);
                        if (player.TryBuyTower<GongiTower>(x, y) == Player.TowerPlacementResult.NotEnoughGold) return;
                    }
                }
                else
                {
                    for (int j = 0; j < ShortFormation.Length; j++)
                    {
                        int x = ShortFormation[j];
                        int y = m_defenseLaneStart + (i * m_defenseLaneDirection);
                        if (player.TryBuyTower<GongiTower>(x, y) == Player.TowerPlacementResult.NotEnoughGold) return;
                    }
                }
            }

        }

        public override void DeploySoldiers()
        {
            if (player.Gold > (m_amountOfAttackRounds * 14) && !m_sendingAttack)
            {
                m_sendingAttack = true;
                m_attackRound = 0;
            }

            if (m_attackRound > m_amountOfAttackRounds)
            {
                m_sendingAttack = false;
                return;
            }

            if (m_sendingAttack)
            {

                for (int i = 0; i < 7; i++)
                {
                    player.TryBuySoldier<GongiSoldier>(i); 
                }
                m_attackRound++;

            }
               
        }

        /*
         * called by the game play environment. The order in which the array is returned here is
         * the order in which soldiers will plan and perform their movement.
         *
         * The default implementation does not change the order. Do better!
         */
        public override List<Soldier> SortedSoldierArray(List<Soldier> unsortedList)
        {
            unsortedList.Sort((a, b) => b.PosY.CompareTo(a.PosY));
            return unsortedList;
        }


        /*
         * called by the game play environment. The order in which the array is returned here is
         * the order in which towers will plan and perform their action.
         *
         * The default implementation does not change the order. Do better!
         */
        public override List<Tower> SortedTowerArray(List<Tower> unsortedList)

        {
            return unsortedList;
        }
    }
}
