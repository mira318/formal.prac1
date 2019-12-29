#include <gtest/gtest.h>
TEST(testinput, regularitycheck)
{
	ASSERT_EQ("ERROR", sol("**", 7, 6));
	ASSERT_EQ("ERROR", sol("a+", 9, 1));
	ASSERT_EQ("ERROR", sol("abc.*", 3, 2));
	ASSERT_EQ("ERROR", sol("aba", 7, 5));
	ASSERT_EQ("ERROR", sol("opt.*..", 4, 1));
	ASSERT_EQ("ERROR", sol("atvf...l*", 9, 3));
	ASSERT_EQ("ERROR", sol("oiy.ji+..lj*kj/", 10, 1));
	ASSERT_EQ("ERROR", sol("hj.*?kl.+", 7, 2));
}
TEST(testinput, correctioncheck)
{
	ASSERT_EQ("ERROR", sol("a+", 5, 8));
	ASSERT_EQ("ERROR", sol("abc.*.", 2, 3));
	ASSERT_EQ("ERROR", sol("ac+dt..", 736, 3457));
}
TEST(checkans, infcheck)
{
	EXPECT_EQ("INF", sol("acb..bab.c.*.ab.ba.+.+*a.", 3, 0));
	EXPECT_EQ("INF", sol("ab.*cab...ba.*.", 2, 0));
	EXPECT_EQ("INF", sol("ba.*", 20, 1));
	EXPECT_EQ("INF", sol("rot..ba.ca.+b.a1.c.tb.+.*neq....", 5, 3));
	EXPECT_EQ("INF", sol("lil..mar..*too..*kas.....", 12, 1));
}
TEST(checkans, notinfcheck)
{
	EXPECT_EQ("4", sol("ab+c.aba.*.bac.+.+*", 3, 1));
	EXPECT_EQ("16", sol("me.tak..*.so..", 5, 1));
	EXPECT_EQ("8", sol("ab.*cab...bad..*.", 4, 0));
	EXPECT_EQ("13", sol("ac+bra...cad..a+*.bra...", 42, 13));
	EXPECT_EQ("11", sol("al.matar....+1+*q.", 7, 4));
}