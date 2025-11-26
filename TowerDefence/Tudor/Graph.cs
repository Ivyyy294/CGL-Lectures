using System;
using System.Collections.Generic;
using GameFramework;

namespace AI_Strategy
{
    public class Graph
    {
        public List<Node> nodes;
        protected Player player;

        public enum Mode
        {
            Home,
            Enemy
        }

        public enum Behavior
        {
            Attack,
            Move
        }
        
        public Graph(Player player)
        {
            this.player = player;
            nodes = new List<Node>();
            for (int y = 0; y < PlayerLane.HEIGHT; y++)
            {
                for (int x = 0; x < PlayerLane.WIDTH; x++)
                {
                    nodes.Add(new Node(x, y));
                }
            }
        }

        public bool GetShortestPath(Node start, out List<Node> path)
        {
            List<PathResult> paths = new List<PathResult>();
            for (int x = 0; x < PlayerLane.WIDTH; x++)
            {
                Node end = nodes[(PlayerLane.HEIGHT - 1) * PlayerLane.WIDTH + x];
                PathResult result = this.GetPath(start, end, Mode.Enemy, Behavior.Move);

                if (result.PathFound)
                {
                    paths.Add(result);
                }
            }

            if (paths.Count == 0)
            {
                path = new List<Node>();
                return false;
            }
            
            paths.Sort((a, b) => a.TotalCost.CompareTo(b.TotalCost));
            path = paths[0].path;
            return true;
        }
        
        public bool GetPathToClosestEnemy(Node start, Node target, out List<Node> path)
        {
            PathResult result = this.GetPath(start, target, Mode.Enemy, Behavior.Attack);
            if (result.PathFound)
            {
                path = result.path;
                return true;    
            }
            
            path = new List<Node>();
            return false;   
        }

        public PathResult GetPath(Node start, Node end, Mode mode, Behavior behvaior)
        {
            PriorityQ<Node> frontier = new PriorityQ<Node>();
            frontier.Enqueue(start, 0);
            Dictionary<Node, Node> cameFrom = new Dictionary<Node, Node>();
            Dictionary<Node, int> costSoFar = new Dictionary<Node, int>();
            cameFrom.Add(start, null);
            costSoFar.Add(start, 0);
            
            HashSet<Node> visited = new HashSet<Node>();
            
            while (frontier.Count > 0)
            {
                Node current = new Node(0, 0);
                
                if (behvaior == Behavior.Move) current = frontier.Dequeue();
                else current = frontier.DequeueMax();
                
                if (visited.Contains(current)) continue;
                visited.Add(current);
                
                if (current == end)
                {
                    break;
                }

                foreach (Node next in this.GetNeighbors(current, mode))
                {
                    int newCost = costSoFar[current] + next.cost;
                    
                    if (!costSoFar.ContainsKey(next) || newCost < costSoFar[next])
                    {
                        costSoFar[next] = newCost;
                        int priority = newCost;
                        frontier.Enqueue(next, priority);
                        cameFrom[next] = current;
                    }

                }
            }

            if (!costSoFar.ContainsKey(end))
            {
                // List<Node> shortPath = new List<Node>();
                // Node currentShort = lastNode;
                // while (currentShort != null)
                // {
                //     shortPath.Add(currentShort);
                //     currentShort = cameFrom[currentShort];
                // }
                //
                // shortPath.Reverse();
                // return new PathResult(shortPath, shortPath[shortPath.Count - 1].cost, false);
                return new PathResult(new List<Node>(), 0, false);   
            }

            List<Node> path = new List<Node>();
            Node currentNode = end;
            while (currentNode != null)
            {
                path.Add(currentNode);
                currentNode = cameFrom[currentNode];
            }

            path.Reverse();
            
            int totalCost = costSoFar[end];
            DebugLogger.Log("Cost to reach end node: " + totalCost);
            
            return new PathResult(path, totalCost, true);
        }
        
        public Node GetNode(int x, int y)
        {
            return nodes.Find(n => n.x == x && n.y == y);
        }

        public void DebugPrint(int x, int y)
        {
            Node displayNode = GetNode(x, y);
            List<Node> neighborsTest = this.GetNeighbors(displayNode, Mode.Enemy);
            DebugLogger.Log("Node: " + displayNode.x + ", " + displayNode.y + "");
            foreach (Node node in neighborsTest)
            {
                DebugLogger.Log("Neighbors: " + node.x + ", " + node.y + " | Cost: " + node.cost);
            }
        }
        
        
        public List<Node> GetNeighbors(Node node, Mode mode)
        {
            int[][] directions = new int[][]
            {
                new int[] { -1,  1 }, //top left
                new int[] {  0,  1 }, //top
                new int[] {  1,  1 }, //top right
                new int[] { -1,  0 }, //left
                new int[] {  1,  0 }, //right
                new int[] { -1, -1 }, //bottom left
                new int[] {  0, -1 }, //bottom
                new int[] {  1, -1 }  //bottom right
            };
            
            List<Node> result = new List<Node>();
            
            foreach(int[] direction in directions)
            {
                int nx = node.x + direction[0];
                int ny = node.y + direction[1];

                if (nx < 0 || ny < 0 || nx >= PlayerLane.WIDTH || ny >= PlayerLane.HEIGHT) continue;
                
                Node neighbor = GetNode(nx, ny);
                if(neighbor == null) continue;

                if (mode == Mode.Enemy)
                {
                    if (player.EnemyLane.GetCellAt(neighbor.x, neighbor.y).Unit == null || player.EnemyLane.GetCellAt(neighbor.x, neighbor.y).Unit.Type == "S")
                    {
                        neighbor.cost = GetNodeCost(neighbor, Mode.Enemy);
                        result.Add(neighbor);
                    }
                }
                else
                {
                    neighbor.cost = GetNodeCost(neighbor, Mode.Home);
                    if(player.HomeLane.GetCellAt(neighbor.x, neighbor.y).Unit == null) result.Add(neighbor);
                }
            }
            
            return result;
        }

        public int GetNodeCost(Node node, Mode mode)
        {
            int range = 2;
            PlayerLane lane = (mode == Mode.Enemy) ? player.EnemyLane : player.HomeLane;
            Unit unit = null;
            int cost = 0;
            
            for (int x = node.x - range; x <= node.x + range; x++)
            {
                for (int y = node.y - range; y <= node.y + range; y++)
                {
                    Cell cell = lane.GetCellAt(x, y);
                    if (cell == null)
                    {
                        continue;
                    }

                    unit = cell.Unit;
                    if (mode == Mode.Enemy)
                    {
                        if (unit != null && unit.Type == "T" && unit.Health > 0)
                        {
                            if (Math.Abs(node.x - x) == 2 || Math.Abs(node.y - y) == 2) cost += 50 * unit.Health;
                            else cost += 100 * unit.Health;
                        }
                        else if (unit != null && unit.Type == "S" && unit.Health > 0)
                        {
                            // if (Math.Abs(node.x - x) == 2 || Math.Abs(node.y - y) == 2) cost += 0;
                            // else cost += 0;
                        }
                        else
                        {
                            // cost = 2;
                        }
                        
                    } 
                    
                    else if (mode == Mode.Home)
                    {
                        if (unit != null && unit.Type == "S" && unit.Health > 0)
                        {
                            // unitsInRange.Add(unit);
                        }
                    }
                }
            }

            // foreach (var entity in unitsInRange)
            // {
            //     if (Math.Abs(node.x - entity.PosX) == 2 || Math.Abs(node.y - entity.PosY) == 2) cost += 2 * entity.Health;
            //     else cost += 1 * entity.Health;
            // }
            
            
            return cost;
        }
        
        // protected bool TryGetTarget(out Unit unit)
        // {
        //     List<Unit> targetsInRange = new List<Unit>();
        //     for (int x = posX - range; x <= posX + range; x++)
        //     {
        //         for (int y = posY - range; y <= posY + range; y++)
        //         {
        //             Cell cell = lane.GetCellAt(x, y);
        //             if (cell == null)
        //             {
        //                 continue;
        //             }
        //
        //             unit = cell.Unit;
        //             if (unit != null && unit.player != player && unit.health > 0)
        //             {
        //                 targetsInRange.Add(unit);
        //                 //return true;
        //             }
        //         }
        //     }
        //
        //     if (targetsInRange.Count > 0)
        //     {
        //         targetsInRange = SortTargetsInRange(targetsInRange);
        //         unit = targetsInRange[0];
        //         return true;
        //     }
        //
        //     unit = null;
        //     return false;
        // }

    }
    
    public class PathResult
    {
        public List<Node> path { get; set; }
        public int TotalCost { get; set; }
        public bool PathFound { get; set; }
            
        public PathResult(List<Node> path, int totalCost, bool pathFound)
        {
            this.path = path;
            this.TotalCost = totalCost;
            this.PathFound = pathFound;
        }
    }
}