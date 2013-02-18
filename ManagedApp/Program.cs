using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace ManagedApp
{
    public static class Program
    {
        [STAThread]
        public static int EntryPoint(string param)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            MessageBox.Show("Переданный параметр: " + param);
            Application.Run(new Form1());
            return 0;
        }
    }
}
