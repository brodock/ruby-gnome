# Copyright (C) 2016  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

class TestGdkPixbuf < Test::Unit::TestCase
  include GdkPixbufTestUtils

  sub_test_case(".new") do
    test "basic hash form" do
      colorspace =  GdkPixbuf::Colorspace::RGB
      width = 100
      height = 100
      has_alpha = true
      bits_per_sample = 8
      pixbuf = GdkPixbuf::Pixbuf.new(:colorspace => colorspace,
                             :has_alpha => has_alpha,
                             :width => width,
                             :height => height,
                             :bits_per_sample => bits_per_sample)
      assert_equal(colorspace, pixbuf.colorspace)
      assert_equal(width, pixbuf.width)
      assert_equal(height, pixbuf.height)
      assert_equal(has_alpha, pixbuf.has_alpha?)
      assert_equal(bits_per_sample, pixbuf.bits_per_sample)
    end

    test "basic legacy form" do
      colorspace =  GdkPixbuf::Colorspace::RGB
      width = 100
      height = 100
      has_alpha = true
      bits_per_sample = 8
      pixbuf = GdkPixbuf::Pixbuf.new(colorspace, has_alpha, bits_per_sample,
                                     width, height)
      assert_equal(colorspace, pixbuf.colorspace)
      assert_equal(width, pixbuf.width)
      assert_equal(height, pixbuf.height)
      assert_equal(has_alpha, pixbuf.has_alpha?)
      assert_equal(bits_per_sample, pixbuf.bits_per_sample)
    end

    test "from_file hash form" do
      filename = fixture_path("gnome-logo-icon.png")
      pixbuf = GdkPixbuf::Pixbuf.new(:file => filename)
      assert_equal(GdkPixbuf::Colorspace::RGB, pixbuf.colorspace)
    end

    test "from_file legacy form" do
      pixbuf = GdkPixbuf::Pixbuf.new(fixture_path("gnome-logo-icon.png"))
      assert_equal(GdkPixbuf::Colorspace::RGB, pixbuf.colorspace)
    end

    r_xpm = [
       "10 10 3 1",
       "   c None",
       ".  c #FE0B0B",
       "+  c #FFFFFF",
       "+.......++",
       "+..    ..+",
       "+..    ..+",
       "+..   ...+",
       "+.......++",
       "+.....++++",
       "+..++..+++",
       "+..++...++",
       "+..+++...+",
       "+..++++..+"]

    test "from_xpm legacy form" do
      pixbuf = GdkPixbuf::Pixbuf.new(r_xpm)
      assert_equal(GdkPixbuf::Colorspace::RGB, pixbuf.colorspace)
    end

    test "from_xpm hash form" do
      pixbuf = GdkPixbuf::Pixbuf.new(:xpm => r_xpm)
      assert_equal(GdkPixbuf::Colorspace::RGB, pixbuf.colorspace)
    end
  end
end
