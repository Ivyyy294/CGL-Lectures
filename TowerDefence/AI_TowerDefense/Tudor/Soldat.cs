using GameFramework;
using System.Collections.Generic;
namespace AI_Strategy
{
    public class Soldat : Soldier
    {
        public override void Move()
        {
            bool attack = false;
            List<Node> neighbors = LeTudorStrategy.Graph.GetNeighbors(LeTudorStrategy.Graph.GetNode(posX, posY), Graph.Mode.Enemy);
            foreach (Node neighbor in neighbors)
            {
                Unit unit = player.EnemyLane.GetCellAt(neighbor.x, neighbor.y).Unit;
                if (unit != null)
                {
                    if (unit.Type == "S" && unit.Health < 6)
                    {
                        attack = true;
                        //the soldiers that are farther away don't redirect towards towers since the towers are outside reach of their vision cone
                    }
                }
            }
            
            if (health <= 6 || attack)
            {
                Unit target = null;
                if (TryGetTargetOutsideReach(out target))
                {
                    var start = LeTudorStrategy.Graph.GetNode(posX, posY);
                    var targetNode = LeTudorStrategy.Graph.GetNode(target.PosX, target.PosY);
                    if(LeTudorStrategy.Graph.GetPathToClosestEnemy(start, targetNode, out List<Node> path))
                    {
                        if(path.Count > 1)
                            if (MoveTo(path[1].x, path[1].y))
                            {
                                DebugLogger.Log("Attacking enemy at: " + target.PosX + ", " + target.PosY);
                                return;
                            }
                    }
                }
                
            }
            
            if (speed > 0 && posY < PlayerLane.HEIGHT)
            {
                if(posY == PlayerLane.HEIGHT - 1)
                {
                    if(MoveTo(posX, posY + 1)) return;
                }
                
                if (LeTudorStrategy.Graph.GetShortestPath(new Node(posX, posY), out List<Node> path))
                {
                    if(path.Count > 1) if(MoveTo(path[1].x, path[1].y)) return;
                }
                else
                {
                    DefaultMove();
                }
                
            }
        }

        private void DefaultMove()
        {
            int x = posX;
            int y = posY;
            for (int i = speed; i > 0; i--)
            {
                if (MoveTo(x, y + i)) return;
                if (MoveTo(x - i, y + i)) return;
                if (MoveTo(x + i, y + i)) return;
                if (MoveTo(x + i, y)) return;
                if (MoveTo(x - i, y)) return;
                if (MoveTo(x - i, y - i)) return;
                if (MoveTo(x + i, y - i)) return;
                if (MoveTo(x, y - i)) return;
                if (MoveTo(x, y)) return;
            }
        } 
        
        protected bool TryGetTargetOutsideReach(out Unit unit)
        {
            int range = 2;
            List<Unit> targetsInRange = new List<Unit>();
            for (int x = posX - range; x <= posX + range; x++)
            {
                for (int y = posY - range; y <= posY + range; y++)
                {
                    Cell cell = lane.GetCellAt(x, y);
                    if (cell == null)
                    {
                        continue;
                    }

                    unit = cell.Unit;
                    if (unit != null && unit.Type == "T" && unit.Health > 0)
                    {
                        targetsInRange.Add(unit);
                    }
                }
            }

            if (targetsInRange.Count > 0)
            {
                targetsInRange = SortTargetsInRange(targetsInRange);
                unit = targetsInRange[0];
                return true;
            }

            unit = null;
            return false;
        }
    }
}