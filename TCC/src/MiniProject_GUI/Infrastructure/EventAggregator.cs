using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiniProject_GUI.Infrastructure
{
    internal class EventAggregator
    {
        private static EventAggregator _instance;
        public static EventAggregator Instance
        {
            get
            {
                if (_instance == null)
                    _instance = new EventAggregator();
                return _instance;
            }
        }

        private readonly Dictionary<Type, List<Delegate>> _subscribers = new Dictionary<Type, List<Delegate>>();
        private readonly object _lock = new object();

        public void Subscribe<T>(Action<T> handler)
        {
            lock (_lock)
            {
                var eventType = typeof(T);
                if (!_subscribers.ContainsKey(eventType))
                    _subscribers[eventType] = new List<Delegate>();
                _subscribers[eventType].Add(handler);
            }
        }

        public void Publish<T>(T eventData)
        {
            List<Delegate> handlers;
            lock (_lock)
            {
                var eventType = typeof(T);
                if (!_subscribers.ContainsKey(eventType))
                    return;
                handlers = new List<Delegate>(_subscribers[eventType]);
            }

            foreach (var handler in handlers)
            {
                (handler as Action<T>)?.Invoke(eventData);
            }
        }

        public void Unsubscribe<T>(Action<T> handler)
        {
            lock (_lock)
            {
                var eventType = typeof(T);
                if (_subscribers.ContainsKey(eventType))
                {
                    _subscribers[eventType].Remove(handler);
                }
            }
        }
    }
}
