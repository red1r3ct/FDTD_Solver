import React, {Component} from 'react';
import PropTypes from 'prop-types';
import CenteredLayout from '../../components/CenteredLayout/CenteredLayout';
import Background from '../../components/Background/Background';
import Header from '../../components/Header/Header';
import {CircularProgress} from 'material-ui/Progress';

export default class Loading extends Component {
	render() {
		return (
			<Background>
				<Header/>
				<CenteredLayout>
					<CircularProgress color="accent"/>
				</CenteredLayout>
			</Background>
		)
	}
}
