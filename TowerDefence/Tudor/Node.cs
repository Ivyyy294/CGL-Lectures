namespace AI_Strategy
{
    public class Node
    {
        public int x, y;
        public int cost = 0;
        public Node(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
        
        public override bool Equals(object obj)
        {
            if (obj is Node other)
                return this.x == other.x && this.y == other.y;
            return false;
        }
        
        public override int GetHashCode()
        {
            // Combine x and y into a single hash code
            return x * 31 + y;
        }
    }
}