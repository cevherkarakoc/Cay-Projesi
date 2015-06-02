using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;

namespace CayWG
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Thread th;
        TcpClient tcpClient;
        NetworkStream nStream;
        StreamReader reader;
        StreamWriter writer;
        bool IsConnect = false;
        public delegate void rictTextBoxDegistir(string text);
 

        public MainWindow()
        {
            
            InitializeComponent();
            richTextBox_mesajlar.IsReadOnly = true;
        }

        public void baglan()
        {
            try
            {
                tcpClient = new TcpClient(textBox_ip.Text, Convert.ToInt16(textBox_port.Text));
                th = new Thread(new ThreadStart(oku));
                th.Start();

                textBox_ad.IsEnabled = false;
                textBox_ip.IsEnabled = false;
                textBox_port.IsEnabled = false;
                btn_baglan.IsEnabled = false;
                btn_baglantiKes.IsEnabled = true;
                textBox_mesaj.IsEnabled = true;
                btn_gonder.IsEnabled = true;
                IsConnect = true;
                richTextBox_mesajlar.AppendText(Environment.NewLine + "Bağlantı kuruldu.");
            }
            catch (Exception)
            {

                richTextBox_mesajlar.AppendText(Environment.NewLine + "Bağlantı kurulamadı.");
            }
        }

        public void oku()
        {
            nStream = tcpClient.GetStream();
            reader = new StreamReader(nStream);
            while (true)
            {
                try
                {
                    string yazi = reader.ReadLine();
                    //MessageBox.Show(yazi);
                    
                    yaz(yazi);
                }
                catch (Exception)
                {
                    yaz("Bağlantı kesildi.");
                    return;
                }
            }
        }
        
        public void yaz(string yazi)
        {
            if (!this.Dispatcher.CheckAccess())
            {
                rictTextBoxDegistir d = new rictTextBoxDegistir(yaz);
                this.Dispatcher.Invoke(d, yazi);
            }
            else
            {
                richTextBox_mesajlar.AppendText(Environment.NewLine + yazi);
            }

        }

        public void baglantiKes()
        {
            if (IsConnect)
            {
                tcpClient.Close();
                IsConnect = false;
            }
        }

        public void mesajGonder()
        {
            if (textBox_mesaj.Text == "")
            {
                return;
            }
            else
            {
                writer = new StreamWriter(nStream);
                writer.WriteLine(textBox_mesaj.Text);
                writer.Flush();
                richTextBox_mesajlar.AppendText(Environment.NewLine + textBox_mesaj.Text);
                textBox_mesaj.Text = "";
            }
        }

        private void btn_baglan_Click(object sender, RoutedEventArgs e)
        {
            baglan();

        }

        private void btn_baglantiKes_Click(object sender, RoutedEventArgs e)
        {
            baglantiKes();
            textBox_ad.IsEnabled = true;
            textBox_ip.IsEnabled = true;
            textBox_port.IsEnabled = true;
            btn_baglan.IsEnabled = true;
            btn_baglantiKes.IsEnabled = false;
            textBox_mesaj.IsEnabled = false;
            btn_gonder.IsEnabled = false;
        }

        private void btn_gonder_Click(object sender, RoutedEventArgs e)
        {
            mesajGonder();
        }

        private void textBox_mesaj_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                mesajGonder();
            }
        }


        private void richTextBox_mesajlar_TextChanged(object sender, TextChangedEventArgs e)
        {
            richTextBox_mesajlar.ScrollToEnd();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            baglantiKes();
        }


        


    }
}
