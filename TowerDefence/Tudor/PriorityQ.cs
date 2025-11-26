using System;
using System.Collections.Generic;

namespace AI_Strategy
{
    public class PriorityQ<T>
    {
        private class Element
        {
            public T Item { get; set; }
            public int Priority { get; set; }
            
            public Element(T item, int priority)
            {
                this.Item = item;
                this.Priority = priority;
            }
        }
        
        private List<Element> elements = new List<Element>();

        public int Count
        {
            get { return elements.Count; }
        }

        public void Enqueue(T item, int priority)
        {
            elements.Add(new Element(item, priority));
        }
        
        public T Dequeue()
        {
            int bestIndex = 0;
            for (int i = 1; i < elements.Count; i++)
            {
                if (elements[i].Priority < elements[bestIndex].Priority)
                {
                    bestIndex = i;
                }
            }
        
            T bestItem = elements[bestIndex].Item;
            elements.RemoveAt(bestIndex);
            return bestItem;
        }
        
        public T DequeueMax()
        {
            int bestIndex = 0;
            for (int i = 1; i < elements.Count; i++)
            {
                if (elements[i].Priority > elements[bestIndex].Priority)
                {
                    bestIndex = i;
                }
            }
        
            T bestItem = elements[bestIndex].Item;
            elements.RemoveAt(bestIndex);
            return bestItem;
        }
    
        public bool TryDequeue(out T item)
        {
            if (elements.Count == 0)
            {
                item = default(T);
                return false;
            }
            item = Dequeue();
            return true;
        }
    }
    
}
