using nframework.nom;
using NOMHandlerLib.Concrete;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiniProject_GUI.Models.Converter
{
    internal interface INOMConvertible
    {
        void Import(NOM nom);
        //NOM Export();
    }
}
