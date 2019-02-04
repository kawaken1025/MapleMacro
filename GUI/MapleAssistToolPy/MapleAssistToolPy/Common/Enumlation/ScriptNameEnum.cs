using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapleAssistToolPy.Common.Enumlation
{
	/// <summary>
	/// スクリプト列挙
	/// </summary>
	public enum ScriptNameEnum
	{
		// Luminous
		CaveloadAisleUp,
		MapleUnion,
		ChuChuIsland,

		// Common
		CoreCreate,
		CoreOpen,
		CoreBreak,
		BuyFamiliar,
		SellEquipment
	}

	/// <summary>
	/// enum拡張クラス
	/// </summary>
    public static class XxxStatusExt
    {
		/// <summary>
		/// EnumのString型を定義し、取得する
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		public static string ObtainScriptName(this ScriptNameEnum value)
		{
		string[] values = {
				// Luminous
				"ケーヴロードの通路(上)",
				"MapleUnion",
				"ChuChuisland",

				// Common
				"CoreCreate",
				"CoreOpen",
				"CoreBreak",
				"BuyFamiliar",
				"SellEquipment",
			};

			// 最後に.uwsをつけて返却する
			return values[(int)value] + ".uws";
		}
    }

}
