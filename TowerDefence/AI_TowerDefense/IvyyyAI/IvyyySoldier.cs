using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IvyyyAI
{
    /*
     * This class derives from Soldier and provides a new move method. Your assignment should
     * do the same - but with your own movement strategy.
     */
    public class IvyyySoldier : Soldier
    {
        bool m_deployed = false;

        public int Depth { get;set;}
        public bool Deployed => m_deployed;

        public void Deploy()
        {
            m_deployed = true;
        }

        protected override List<Unit> SortTargetsInRange(List<Unit> targets)
        {
            return targets.OrderByDescending(x => x.Health).ToList();
        }

        /*
         * This move method is a mere copy of the base movement method.
         */
        public override void Move()
        {
            IvyyyPosition waypoint = new();

            if (!IsTowerInRange(ref waypoint))
            {
                if (m_deployed || posY >= Depth)
                {
                    base.Move();
                    waypoint.x = posX;
                    waypoint.y = posY + 1;
                }
                else
                {
                    waypoint.x = posX;
                    waypoint.y = posY + (posY < Depth-1 ? 1 : 0);
                }
            }

            ApproachWaypoint (ref waypoint);
        }

        private bool IsTowerInRange(ref IvyyyPosition waypoint)
        {
            List<Tower> towers = new List<Tower>();

            for (int x = Math.Max(0, PosX-1); x < Math.Min(7, PosX+1); ++x)
            {
                for (int y = Math.Max(0, PosY + 1); y < Math.Min(20, PosY + 3); ++y)
                {
                    Unit unit = player.EnemyLane.GetCellAt(x, y).Unit;

                    if (unit is Tower)
                        towers.Add ((Tower)unit);
                }
            }

            towers = towers.OrderByDescending(x=>x.Health).ToList();

            if (towers.Count > 0)
            {
                Tower tower = towers[0];
                waypoint.x = tower.PosX;
                waypoint.y = tower.PosY;
                return true;
            }

            return false;
        }

        private void ApproachWaypoint (ref IvyyyPosition waypoint)
        {
            int xOffset = posX - waypoint.x;
            int yOffset = posY - waypoint.y;

            int xDiff = Math.Abs (xOffset);
            int yDiff = Math.Abs (yOffset);

            int x = posX - Math.Sign (xOffset);
            int y = posY - Math.Sign(yOffset);

            for (int i = speed; i > 0; i--)
            {
                if (xDiff >= yDiff)
                    TryMoveX (x, y);
                else
                    TryMoveY (x, y);
            }
        }

        private void TryMoveX (int x, int y)
        {
            //Try linear x
            if (MoveTo(x, posY)) return;
            //Try Diagona x
            if (MoveTo(x, y)) return;
            //try linear y
            if (MoveTo(posX, y)) return;
        }

        private void TryMoveY(int x, int y)
        {
            //Try linear Y
            if (MoveTo(PosX, y)) return;
            //Try Diagona y
            if (MoveTo(x, y)) return;
            //try linear x
            if (MoveTo(x, PosY)) return;
        }
    }
}
