import React from 'react';
import AppBar from 'material-ui/AppBar';
import Toolbar from 'material-ui/Toolbar';
import Typography from 'material-ui/Typography';
import Button from 'material-ui/Button';
import IconButton from 'material-ui/IconButton';
import MenuIcon from 'material-ui-icons/Menu';

export const Header = ({ children }) => (
	<AppBar position="static">
		<Toolbar>
			<IconButton color="contrast" aria-label="Menu">
				<MenuIcon />
			</IconButton>
			<Typography type="title" color="inherit">
				FDTD Solver
			</Typography>
		</Toolbar>
	</AppBar>
);

export default Header;
