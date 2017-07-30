const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
	devtool: 'eval-source-map',
	entry: ['babel-polyfill', 'whatwg-fetch', path.resolve('./frontend/index.js')],
	output: {
		path: path.resolve('./static'),
		filename: 'bundle.js',
	},
	module: {
		rules: [
			{
				test: /\.jsx?$/,
				exclude: [/node_modules/],
				use: ['babel-loader'],
			},
			{
				test: /\.css$/,
				use: ['style-loader', 'css-loader?modules=1', 'postcss-loader']
			}
		]
	},
	plugins: [
		new HtmlWebpackPlugin({
			template: 'frontend/index.html'
		}),
	],
};