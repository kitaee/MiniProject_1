using nframework.nom;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiniProject_GUI.Models.Converter
{
    internal static class NOMConverter
    {
        public static T Import<T>(NOM nom) where T : INOMConvertible, new()
        {
            var obj = new T();
            obj.Import(nom);
            return obj;
        }

        //public static NOM Export<T>(T obj) where T : INOMConvertible
        //{
        //    return obj.Export();
        //}
    }
}
